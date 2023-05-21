from pathlib import Path
from sys import argv

from PIL import Image


def convert(src, out, write_size=True):
    img = Image.open(src).convert('RGBA')
    width, height = img.size

    if height % 8:
        print('Warning: height of the image isn\'t divisible by 8')

    is_alpha = False
    for y in range(height):
        for x in range(width):
            is_alpha = is_alpha or img.getpixel((x, y))[3] != 0xff

    if write_size:
        out.write(f'{width}, {height}')

    for y in range(0, height, 8):
        for x in range(width):
            a = b = 0

            for p in range(8):
                if y + p == height:
                    break

                pixel = list(img.getpixel((x, y + p)))

                if sum(pixel) - pixel[3] not in (0xff * 3, 0x00):
                    print(f'Warning: pixel at ({x}, {y + p}) is coloured')

                if pixel[3] not in (0xff, 0x00):
                    print(f'Warning: pixel at ({x}, {y + p} has float transparency')

                a |= (pixel[3] == 0xff) << p
                b |= (sum(pixel) - pixel[3] == 0xff * 3 and pixel[3] == 0xff) << p

            out.write(f', 0x{b:02x}')
            if is_alpha:
                out.write(f', 0x{a:02x}')


def process(src, out):
    # Write new images sequence
    out.write(f'const uint8_t IMAGE_{src.stem.upper()}[] PROGMEM = {{  //\n')

    if src.is_dir():
        # If directory present, proccess files as one sequence
        for i, file in enumerate(sorted(src.glob('*'))):
            convert(file, out, not i)

    else:
        convert(src, out)

    out.write('};\n')


def main():
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
            out.write('\n')


if __name__ == '__main__':
    main()
