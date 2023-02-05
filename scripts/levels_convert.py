from pathlib import Path
from sys import argv

byte_map = {
    0x00: 0x00,
    0x01: 0x01,
    0x20: 0x02
}


def compress(data):
    """ Todo """
    return data


def convert(src_path, out):
    src = Path(src_path).absolute()

    with open(src, 'rb') as file:
        data = compress(file.read())

    out.write(f'const uint8_t LEVEL_{src.stem}[] PROGMEM = {{  //\n')
    width, height = data[6:8]

    # Copy metadata
    out.write(', '.join(f'0x{i:02x}' for i in data[:8]))

    for byte in data[8:8 + width * height]:
        out.write(f', 0x{byte_map.get(byte, 0):02x}')

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

        for src in argv[2:]:
            print(f'Processing {src}')
            convert(src, out)
            levels.add(int(Path(src).stem))
            out.write('\n')

        out.write('const uint8_t* const LEVELS[] = { //\n')
        out.write(', '.join(f'LEVEL_{i}' for i in levels))
        out.write('};\n')


if __name__ == '__main__':
    main()
