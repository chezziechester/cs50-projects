from cs50 import get_int

# note: this was before i knew // was a thing

def checkSum(number, double):
    # recursively calls itself once for checking every other number starting from last digit
    if double == True:
            single = checkSum(number * 10, False)

    # if starting from second to last digit, multiplier is 2
    multiplier = 2
    sum = 0

    # if starting from last digit, multiplier is 1
    if double == False:
        multiplier = 1

    number /= 10

    while number >= 1:
        tmp = int(number % 10)

        # only for second to last digit, because multiplying 2 by any number larger than 5 results in >=10
        if tmp * multiplier >= 10:
            # stores the first and last digit into separate variables and then adds it to sum
            # adding the digits, not the product
            # have to typecast int, otherwise it gets added as a float
            first = int((tmp * multiplier)/10)
            second = (tmp * multiplier) % 10
            sum += first + second

        # if the resulting number is not two digits, directly add it to sum
        else:
            sum += tmp * multiplier

        number /= 100
        int(number)

    # returns sum for the "double" function to use it
    if double == False:
        return sum

    # checks to see if last digit is 0, is so, then it is valid
    if (sum + single) % 10 == 0:
        return 1
    else:
        print("INVALID")
        return 0

def checkCard(number):
    # divides the card number by 10^n to check if the first two digits match
    if int(number/(10 ** 13)) == 34 or int(number/(10 ** 13)) == 37:
        print("AMEX")
        return 0
    for i in [51, 52, 53, 54, 55]:
        if int(number/(10 ** 14)) == i:
            print("MASTERCARD")
            return 0
    if int(number/(10 ** 12)) == 4 or int(number/(10 ** 15)) == 4:
        print("VISA")
        return 0
    print("INVALID")
    return 1

def main():
    input = get_int("Number: ")
    if checkSum(input, True):
        checkCard(input)

main()