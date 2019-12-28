import random
player = int(input("请输入出的拳:"))

computer = random.randint(1,3)

print("电脑出的拳是:%d - 玩家出的拳是:%d"%(computer,player))

if ((player == 1 and computer == 2)
        or (player == 2 and computer == 3)
        or (player == 3 and computer == 1)):

    print("ko!!")

elif player == computer:

    print("==")

else:

    print("loser")