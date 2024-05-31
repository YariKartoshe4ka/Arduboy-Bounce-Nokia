from pathlib import Path
from sys import argv

byte_map = {
    0x00: 0x00,  # Empty
    0x01: 0x01,  # Block
    0x20: 0x02,  # Ramp top-left
    0x21: 0x03,  # Ramp top-right
    0x07: 0x07,  # Crystall
    0x1d: 0x08,  # Crystall ball

    0x03: 0x20,  # Spike down
    0x04: 0x21,  # Spike left
    0x05: 0x22,  # Spike up
    0x06: 0x23,  # Spike right

    0x0d: 0x10,  # Ring vertical (up part)
    0x0e: 0x11,  # Ring vertical (down part)
    0x0f: 0x12,  # Ring horizontal (left part)
    0x10: 0x13,  # Ring horizontal (right part)
    0x15: 0x14,  # Big ring vertical (up part)
    0x16: 0x15,  # Big ring vertical (down part)
    0x17: 0x16,  # Big ring horizontal (left part)
    0x18: 0x17,  # Big ring horizontal (right part)

    0x27: 0x30,  # Deflator
    0x2b: 0x31,  # Inflator

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


def _convert_objects(objects):
    objects = objects.replace(b'\x09\x09', b'\xe0\xe1', 1).replace(b'\x09\x09', b'\xe2\xe3', 1)
    return bytes(byte_map.get(i, 0) for i in objects)


def _convert_spiders(spiders):
    n, spiders = spiders[0], spiders[1:]
    res = bytes([n])

    for i in range(n):
        chunk = spiders[i * 8:(i + 1) * 8]
        l, t, r, b, h, v, th, tv = chunk
        dx, dy = r - l - 2, b - t - 2

        res += bytes([l, t, dx, dy, th, tv])

    return res


def parse_level(src):
    with open(src, 'rb') as file:
        data = file.read()

    # Parse level byte stream to parts
    meta = Meta(data[:8])
    objects = data[8:8 + meta.width * meta.height]
    spiders = data[8 + meta.width * meta.height:]

    # Convert objects and spiders with our schema
    objects = _convert_objects(objects)
    spiders = _convert_spiders(spiders)

    return bytes(meta) + objects + spiders


def main():
    levels = {}

    fxdata_size = 0
    fxdata_path = Path(argv[1])

    for src in map(Path, argv[3:]):
        print(f'Processing {src}')

        level_no = int(src.stem)
        levels[level_no] = parse_level(src)
        fxdata_size += len(levels[level_no])

    levels = dict(sorted(levels.items()))

    with open(fxdata_path, 'wb') as fxdata:
        for level in levels.values():
            fxdata.write(level)

    header_path = Path(argv[2])
    with open(header_path, 'w') as header:
        header.write(
            '#pragma once\n\n'
            '#include <Arduboy2.h>\n\n'
            'using uint24_t = __uint24;\n\n\n'
            f'const uint16_t FX_DATA_PAGE = {hex(0x10000 - (fxdata_size + 255) // 256)};\n\n'
        )

        header.write('const uint24_t LEVELS[] = { //\n')

        offsets = []
        cur_offset = 0
        for _, level in levels.items():
            offsets.append(hex(cur_offset))
            cur_offset += len(level)

        header.write(', '.join(offsets))
        header.write('};\n')


if __name__ == '__main__':
    main()
