import string

if __name__ == "__main__":
    letters = list(string.ascii_lowercase)
    s = 3 * "b"
    for i in range(2, 26):
        s += 2 * letters[i]
    s += "a"
    v = "GYB"
    for i in range(2, 26):
        v += "GB"
    v += "Y"
    print(s, v)