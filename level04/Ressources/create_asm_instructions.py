import re

# splitting the string into arrays of 2 and encoding them
s = re.findall('..', "/home/users/level05".encode("utf-8").hex())
print(s)
leftover = 0
# merging them back together in reverse, with the push instruction (x68) added at the beginning 
for i in range(len(s) - 4, 0, -4):
    print('\\x68\\x' + '\\x'.join(s[i : i + 4]), end='')
    leftover = i
if leftover > 0:
    padding = ''
    # adding '/' if the string len is not a multiple of 4 to complete the string, since chmod(//users/[...]) will work. dunno which other character can be used
    for i in range (4 - leftover):
        padding += '\\x2f'
    print('\\x68' + padding + '\\x' + '\\x'.join(s[0 : leftover]))
