from pathlib import Path
from sys import argv

byte_map = {
    0x00: 0x00,  # Empty
    0x01: 0x01,  # Block
    0x20: 0x02,  # Ramp left
    0x07: 0x07,  # Crystall
    0x1d: 0x08,  # Crystall ball
    0x03: 0x03,  # Spike down
    0x0d: 0x10,  # Ring vertical (up part)
    0x0e: 0x11,  # Ring vertical (down part)
    0x0f: 0x12,  # Ring horizontal (left part)
    0x10: 0x13,  # Ring horizontal (right part)
    0xe0: 0xe0,  # End (left-up part)
    0xe1: 0xe1,  # End (right-up part)
    0xe2: 0xe2,  # End (down-left part)
    0xe3: 0xe3,  # End (down-right part)
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

    objects = objects.replace(b'\x09\x09', b'\xe0\xe1', 1).replace(b'\x09\x09', b'\xe2\xe3', 1)
    return bytes(byte_map.get(i, 0) for i in objects)


def process(src, out):
    with open(src, 'rb') as file:
        data = file.read()

    # Parse level byte stream to parts
    meta = Meta(data[:8])
    objects = data[8:8 + meta.width * meta.height]
    spiders = data[8 + meta.width * meta.height:]  # noqa: F841

    # Convert objects with our schema
    objects = convert(objects)

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
