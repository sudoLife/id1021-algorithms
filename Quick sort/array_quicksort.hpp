#if !defined(ARRAY_QUICKSORT_HPP)
#define ARRAY_QUICKSORT_HPP

#include <iostream>
#include <vector>

namespace array
{

    template <typename T>
    void print(const std::vector<T> &vec, int low, int high)
    {
        for (int i = low; i <= high; i++)
        {
            std::cout << vec[i] << ' ';
        }
        std::cout << '\n';
    }

    template <typename T>
    inline void swap(T &a, T &b)
    {
        T temp = a;
        a = b;
        b = temp;
    }

    template <typename T>
    inline int partition(std::vector<T> &arr, int low, int high)
    {
        auto pivot = arr[high]; // choosing the last element as pivot
        int i = low - 1;
        // print(arr, low, high);
        for (int j = low; j <= high - 1; j++)
        {
            if (arr[j] < pivot)
            {
                i++; // this ensures that we never touch elements that have been swapped, again.
                // std::cout << "swapping " << arr[i] << " with " << arr[j] << '\n';
                swap(arr[i], arr[j]);
                // print(arr, low, high);
            }
        }
        // putting the pivot between smaller and larger values
        // std::cout << "swapping " << arr[i + 1] << " with " << arr[high] << '\n';
        swap(arr[i + 1], arr[high]);
        return (i + 1);
    }

    template <typename T>
    void quicksort(std::vector<T> &arr, int start, int stop)
    {
        if (start < stop)
        {
            auto pivot_ind = partition(arr, start, stop);
            // std::cout << "Pivot: arr[" << pivot_ind << "] = " << arr[pivot_ind] << '\n';

            quicksort(arr, start, pivot_ind - 1);
            quicksort(arr, pivot_ind + 1, stop);
        }
    }

}

#endif // ARRAY_QUICKSORT_HPP
