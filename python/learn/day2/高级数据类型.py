#列表
name_list = ["zhangsan","lisi","wangwu"]
print(name_list.index("lisi"))

name_list[1] = "renjg"
print(name_list[1])

name_list.append("zhao6")
name_list.insert(1,"liu7")

temp_list = ["ww","ee","ss"]
name_list.extend(temp_list)

name_list.remove("wangwu")
name_list.pop(0)
#name_list.clear()
#name_list[1] =
del name_list[0]
list_len = len(name_list)
print(name_list)
print(list_len)
name_list.remove("renjg")
print(name_list)
#name_list.sort()
print(name_list)
name_list.sort(reverse=True)
print(name_list)