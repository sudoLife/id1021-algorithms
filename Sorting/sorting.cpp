#include <chrono>
#include <cstring>
#include <ctime>
#include <iostream>

typedef std::chrono::high_resolution_clock hclock;
using std::chrono::duration_cast;
typedef std::chrono::microseconds us;
typedef std::chrono::nanoseconds ns;

// this will overwrite arr
void merge(int *left, int left_size, int *right, int right_size, int *arr)
{
    int arr_i = 0;
    int left_i = 0;
    int right_i = 0;
    while (left_i < left_size && right_i < right_size)
    {
        if (left[left_i] <= right[right_i])
        {
            arr[arr_i] = left[left_i];
            left_i++;
        }
        else
        {
            arr[arr_i] = right[right_i];
            right_i++;
        }
        arr_i++;
    }
    // Only one of these will fire
    while (left_i < left_size)
    {
        arr[arr_i++] = left[left_i++];
    }
    while (right_i < right_size)
    {
        arr[arr_i++] = right[right_i++];
    }
}

void merge_sort(int *arr, int len)
{
    if (len == 1) // already sorted
        return;

    // split the array into two parts
    int left_size = len / 2;
    int right_size = len - (len / 2); // in case it's not even

    auto left = new int[left_size];
    auto right = new int[right_size];

    // and call merge_sort on them
    std::memcpy(left, arr, sizeof(int) * left_size);
    std::memcpy(right, arr + len / 2, sizeof(int) * right_size);

    merge_sort(left, left_size);
    merge_sort(right, right_size);

    // now we just have to merge them
    merge(left, left_size, right, right_size, arr);
}

void insertion_sort(int *arr, int len)
{
    for (int i = 1; i < len; i++)
    {
        auto j = i;

        // move the element until it's in the right place or beginning
        while (j > 0 && arr[j] < arr[j - 1])
        {
            auto temp = arr[j - 1]; // could also do an XOR swap here
            arr[j - 1] = arr[j];
            arr[j] = temp;
            j--;
        }
    }
}

bool is_sorted(int *arr, int len)
{
    for (int i = 1; i < len; i++)
    {
        if (arr[i - 1] > arr[i])
        {
            return false;
        }
    }

    return true;
}

void selection_sort(int *arr, int len)
{
    for (int i = 0; i < len - 1; i++)
    {
        auto smallest = arr[i];
        int candidate_pos = i;

        for (int j = i + 1; j < len; j++)
        {
            if (arr[j] < smallest)
            {
                smallest = arr[j];
                candidate_pos = j;
            }
        }
        if (candidate_pos != i)
        {
            // swapping
            arr[candidate_pos] = arr[i];
            arr[i] = smallest;
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <N>\n";
        return 1;
    }

    srand(time(NULL));

    int N = std::atoi(argv[1]);

    auto arr = new int[N];

    for (int i = 0; i < N; i++)
    {
        arr[i] = rand() % (10 * N); // 0..10N
    }

    hclock::time_point t1, t2;

    t1 = hclock::now();
    merge_sort(arr, N);
    t2 = hclock::now();

    auto dt = duration_cast<us>(t2 - t1).count();

    std::cout << N << " " << dt << '\n';

    // std::cout << "Sorted: " << is_sorted(arr, N) << '\n';

    delete[] arr;

    return 0;
}
