def mutiple_table():
    row = 1
    while row <= 9:
        col = 1
        while col <= row:
            print("%d * %d = %d"%(col,row,col*row),end = " \t")
            col += 1
        row += 1
        print("")

