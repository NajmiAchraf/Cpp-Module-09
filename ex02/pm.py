import random


# merge two sorted arrays with printing every step
def merge(left_arr, right_arr):
    print("Merge")
    result = []
    i = j = 0
    while i < len(left_arr) and j < len(right_arr):
        if left_arr[i] < right_arr[j]:
            result.append(left_arr[i])
            i += 1
        else:
            result.append(right_arr[j])
            j += 1
        print(result)
    result += left_arr[i:]
    result += right_arr[j:]
    print(result)
    return result


# insertion sort with printing every step
def insertion_sort(arr):
    print("Insertion Sort")
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and key < arr[j]:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key
        print(arr)
    return arr


# Merge Insertion Sort with Printing Every Step
def merge_insert_sort(arr):
    print("Merge Insertion Sort")
    # base case
    if len(arr) <= 5:
        return insertion_sort(arr)

    # recursive case
    mid = len(arr) // 2
    left_arr = arr[:mid]
    right_arr = arr[mid:]

    # sort the left and right subarrays
    left_arr = merge_insert_sort(left_arr)
    right_arr = merge_insert_sort(right_arr)

    # merge the sorted subarrays
    return merge(left_arr, right_arr)


if __name__ == '__main__':
    arr = [x for x in range(20, 0, -1)]
    print(merge_insert_sort(arr))
