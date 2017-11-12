from sys import stdin
from math import lgamma, exp, log


def get_num_lt_or_eq(l, num):
    """

    :param l: The list we are searching
    :param num: Upper bound
    :return: The number of elements in l that are less than or equal to num.
    """
    # binary search for the position of num
    left = 0
    right = len(l) - 1

    num += 1

    while right >= left:
        pos = (left + right) // 2
        if l[pos] < num:
            left = pos + 1
            continue
        if l[pos] >= num:
            right = pos - 1
            continue
        return pos
        break
    
    return left

def get_percentile(l, p):
    """

    :param l: The list we are searching
    :param p: The percentile we want to find. Must be in the interval [0, 1)
    :return: The element at position p*listsize
    """
    position = int(len(l) * p)
    return l[position]


def main():
    kc_history = []
    # read the killcount data from the input file and put it in kc_history
    for line in stdin:
        num = int(line)
        kc_history.append(num)

    # sort the data to make it easier to work with
    kc_history.sort()
    print("Number of data points: {}".format(len(kc_history)))
    print("Killcount - # of simulations having completed the crossbows at this killcount")

    average = sum(kc_history) // len(kc_history)

    for x in range(kc_history[len(kc_history)-1]//1000+2):
        x = x * 1000
        print("{}\t{}".format(x, get_num_lt_or_eq(kc_history, x)))
    
    print("1% Luckiest: {}".format(get_percentile(kc_history, 0.01)))
    print("5% Luckiest: {}".format(get_percentile(kc_history, 0.05)))
    print("50% Median: {}".format(get_percentile(kc_history, 0.5)))
    print("Average {}".format(average))
    print("5% Unluckiest: {}".format(get_percentile(kc_history, 0.95)))
    print("1% Unluckiest: {}".format(get_percentile(kc_history, 0.99)))


main()
