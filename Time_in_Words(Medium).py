'''
CODE
'''

words = ["one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "quarter", "sixteen", "seventeen", "eighteen", "nineteen", "twenty", "twenty one", "twenty two", "twenty three", "twenty four", "twenty five", "twenty six", "twenty seven", "twenty eight", "twenty nine", "half"]

# Complete the timeInWords function below.
def timeInWords(h, m):
    result = ""
    if m <= 30:
        if m == 0:
            result = result + words[h-1] + " o' clock"
        elif m == 15 or m == 30:
            result = result + words[m-1] + " past " + words[h-1]
        elif m == 1:
            result = result + words[m-1] + " minute past " + words[h-1]
        else:
            result = result + words[m-1] + " minutes past " + words[h-1]
    else:
        m = 60 - m
        if m == 15:
            result = result + words[m-1] + " to " + words[h]
        else:
            result = result + words[m-1] + " minutes to " + words[h]

    return result


if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    h = int(input())

    m = int(input())

    result = timeInWords(h, m)

    fptr.write(result + '\n')

    fptr.close()