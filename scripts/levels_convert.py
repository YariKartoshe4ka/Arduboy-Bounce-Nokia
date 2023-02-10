from pathlib import Path
from sys import argv

byte_map = {
    0x00: 0x00,  # Empty
    0x01: 0x01,  # Block
    0x20: 0x02,  # Ramp left
    0x0d: 0x10,  # Ring vertical
    0x0e: 0x00,  # Ring vertical (down part)
    0x0f: 0x11,  # Ring horizontal
    0x10: 0x00,  # Ring horizontal (right part)
    0x09: 0xa0,  # End
}


class Meta:
    def __init__(self, meta):
        self.__meta = meta

        (self.pos_x, self.pos_y, self.big_ball, self.end_x, self.end_y, self.rings,
            self.width, self.height) = meta

    def __bytes__(self):
        return self.__meta


def convert(objects):
    """Convert level objects"""

    objects = objects.replace(b'\x09\x09', b'\x09\x00', 1).replace(b'\x09\x09', b'\x00\x00')
    return bytes(byte_map.get(i, 0) for i in objects)


def compress(objects):
    """Copmress level objects"""

    res = b''

    prev_byte = b'\x00'
    byte_cnt = 0

    for byte in objects:
        byte = bytes([byte])

        if byte == prev_byte and byte_cnt < 255:
            byte_cnt += 1
        else:
            if byte_cnt > 3:
                res += prev_byte + b'\xff' + bytes([byte_cnt])
            else:
                res += prev_byte * byte_cnt

            byte_cnt = 1

        prev_byte = byte

    if byte_cnt > 3:
        res += prev_byte + b'\xff' + bytes([byte_cnt])
    else:
        res += prev_byte * byte_cnt

    return res


def process(src, out):
    with open(src, 'rb') as file:
        data = file.read()

    # Parse level byte stream to parts
    meta = Meta(data[:8])
    objects = data[8:8 + meta.width * meta.height]
    spiders = data[8 + meta.width * meta.height:]  # noqa: F841

    # Convert objects with our schema and compress
    objects = compress(convert(objects))

    # Combine all data in one byte stream
    data = bytes(meta) + objects

    # Write data in hex format to file
    out.write(f'const uint8_t LEVEL_{src.stem}[] PROGMEM = {{  //\n')
    out.write(', '.join(f'0x{i:02x}' for i in data))
    out.write('};\n')


def main():
    levels = set()

    with open(argv[1], 'w') as out:
        out.write(
            '#pragma once\n'
            '\n'
            '#include <Arduboy2Ex.h>\n'
            '\n'
        )

        for src in map(Path, argv[2:]):
            print(f'Processing {src}')
            process(src, out)
            levels.add(int(src.stem))
            out.write('\n')

        out.write('const uint8_t* const LEVELS[] = { //\n')
        out.write(', '.join(f'LEVEL_{i}' for i in levels))
        out.write('};\n')


if __name__ == '__main__':
    main()
