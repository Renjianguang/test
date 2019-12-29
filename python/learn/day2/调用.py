def print_line(char):
    print(char * 5)


def print_lines(num,char):
    row = 0
    while row < num:
        print_line(char)
        row += 1
print_lines(5, "x")


