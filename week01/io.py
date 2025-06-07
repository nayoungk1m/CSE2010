import sys

def read_input(input_file:str) -> list:
    with open(input_file, 'r') as f:
        lines = f.readlines()
    return lines

def calculate(line:list) -> list:
    output_lines = []
    for line in lines:
        company, price, shares = line.split()
        price, shares = float(price), int(shares)
        total = price * shares
        output_lines.append(f"{company} {total}\n")
    return output_lines

def write_output(output_file:str, lines:list) -> None:
    with open(output_file, 'w') as f:
        for line in lines:
            f.write(line)

if __name__ == "__main__":
    if len(sys.argv) == 3:
        input_file = sys.argv[1]
        output_file = sys.argv[2]
        lines = read_input(input_file)
        output_lines = calculate(lines)
        write_output(output_file, output_lines)