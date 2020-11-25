#include "sortutils.hpp"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>

void initializeRawArrayFromStdArray(const std::array<int, HOW_MANY_ELEMENTS>& source, int dest[])
{
    for (std::size_t i = 0; i < source.size(); ++i)
    {
        dest[i] = source[i];
    }
}

void organPipeStdArray(std::array<int, HOW_MANY_ELEMENTS>& data)
{
    auto midIndex = data.size() / 2;

    if (data.size() % 2)
    {
        for (std::size_t i = 1; i <= midIndex; ++i)
        {
            data[midIndex + i] = data[midIndex - i];
        }
    }
    else
    {
        for (std::size_t i = 0; i < midIndex; ++i)
        {
            data[midIndex + i] = data[midIndex - i - 1];
        }
    }
}

void evaluateRawArray(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated)
{
    /* Time sort */
    // 1. Random Time
    std::chrono::milliseconds randomTime(0);
    std::chrono::steady_clock clock;
    for (auto i = HOW_MANY_TIMES; i > 0; --i)
    {
        int randomCpy[HOW_MANY_ELEMENTS];
        initializeRawArrayFromStdArray(random, randomCpy);

        auto start = clock.now();
        std::sort(randomCpy, randomCpy + HOW_MANY_ELEMENTS);
        auto end = clock.now();

        randomTime += std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    }

    // 2. Sorted Time
    std::chrono::milliseconds sortedTime(0);
    for (auto i = HOW_MANY_TIMES; i > 0; --i)
    {
        int sortedCpy[HOW_MANY_ELEMENTS];
        initializeRawArrayFromStdArray(sorted, sortedCpy);

        auto start = clock.now();
        std::sort(sortedCpy, sortedCpy + HOW_MANY_ELEMENTS);
        auto end = clock.now();

        sortedTime += std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    }

    // 3. Reversed Time
    std::chrono::milliseconds reversedTime(0);
    for (auto i = HOW_MANY_TIMES; i > 0; --i)
    {
        int reversedCpy[HOW_MANY_ELEMENTS];
        initializeRawArrayFromStdArray(reversed, reversedCpy);

        auto start = clock.now();
        std::sort(reversedCpy, reversedCpy + HOW_MANY_ELEMENTS);
        auto end = clock.now();

        reversedTime += std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    }

    // 4. Organ Pipe Time
    std::chrono::milliseconds organPipeTime(0);
    for (auto i = HOW_MANY_TIMES; i > 0; --i)
    {
        int organPipeCpy[HOW_MANY_ELEMENTS];
        initializeRawArrayFromStdArray(organPipe, organPipeCpy);

        auto start = clock.now();
        std::sort(organPipeCpy, organPipeCpy + HOW_MANY_ELEMENTS);
        auto end = clock.now();

        organPipeTime += std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    }

    // 5. Rotated Time
    std::chrono::milliseconds rotatedTime(0);
    for (auto i = HOW_MANY_TIMES; i > 0; --i)
    {
        int rotatedCpy[HOW_MANY_ELEMENTS];
        initializeRawArrayFromStdArray(rotated, rotatedCpy);

        auto start = clock.now();
        std::sort(rotatedCpy, rotatedCpy + HOW_MANY_ELEMENTS);
        auto end = clock.now();

        rotatedTime += std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    }

    // Print stats
    std::cout << " --- Raw Array Performance ---" << std::endl;
    std::cout << "Random Time     :" << randomTime.count() << " ms" << std::endl;
    std::cout << "Sorted Time     :" << sortedTime.count() << " ms" << std::endl;
    std::cout << "Reversed Time   :" << reversedTime.count() << " ms" << std::endl;
    std::cout << "Organ Pipe Time :" << organPipeTime.count() << " ms" << std::endl;
    std::cout << "Rotated Time    :" << rotatedTime.count() << " ms" << std::endl;
    std::cout << std::endl;
}

void evaluateStdArray(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated)
{
    /* Time sort */
    // 1. Random Time
    std::chrono::milliseconds randomTime(0);
    std::chrono::steady_clock clock;
    for (auto i = HOW_MANY_TIMES; i > 0; --i)
    {
        SourceArray randomCpy = random;

        auto start = clock.now();
        std::sort(randomCpy.begin(), randomCpy.end());
        auto end = clock.now();

        randomTime += std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    }

    // 2. Sorted Time
    std::chrono::milliseconds sortedTime(0);
    for (auto i = HOW_MANY_TIMES; i > 0; --i)
    {
        SourceArray sortedCpy = sorted;

        auto start = clock.now();
        std::sort(sortedCpy.begin(), sortedCpy.end());
        auto end = clock.now();

        sortedTime += std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    }

    // 3. Reversed Time
    std::chrono::milliseconds reversedTime(0);
    for (auto i = HOW_MANY_TIMES; i > 0; --i)
    {
        SourceArray reversedCpy = reversed;

        auto start = clock.now();
        std::sort(reversedCpy.begin(), reversedCpy.end());
        auto end = clock.now();

        reversedTime += std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    }

    // 4. Organ Pipe Time
    std::chrono::milliseconds organPipeTime(0);
    for (auto i = HOW_MANY_TIMES; i > 0; --i)
    {
        SourceArray organPipeCpy = organPipe;

        auto start = clock.now();
        std::sort(organPipeCpy.begin(), organPipeCpy.end());
        auto end = clock.now();

        organPipeTime += std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    }

    // 5. Rotated Time
    std::chrono::milliseconds rotatedTime(0);
    for (auto i = HOW_MANY_TIMES; i > 0; --i)
    {
        SourceArray rotatedCpy = rotated;

        auto start = clock.now();
        std::sort(rotatedCpy.begin(), rotatedCpy.end());
        auto end = clock.now();

        rotatedTime += std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    }

    // Print stats
    std::cout << " --- std::array Performance ---" << std::endl;
    std::cout << "Random Time     :" << randomTime.count() << " ms" << std::endl;
    std::cout << "Sorted Time     :" << sortedTime.count() << " ms" << std::endl;
    std::cout << "Reversed Time   :" << reversedTime.count() << " ms" << std::endl;
    std::cout << "Organ Pipe Time :" << organPipeTime.count() << " ms" << std::endl;
    std::cout << "Rotated Time    :" << rotatedTime.count() << " ms" << std::endl;
    std::cout << std::endl;
}

void evaluateStdVector(const SourceArray& random, const SourceArray& sorted, const SourceArray& reversed, const SourceArray& organPipe, const SourceArray& rotated)
{
    /* Time sort */
    // 1. Random Time
    std::chrono::milliseconds randomTime(0);
    std::chrono::steady_clock clock;
    for (auto i = HOW_MANY_TIMES; i > 0; --i)
    {
        std::vector<int> randomCpy(random.begin(), random.end());

        auto start = clock.now();
        std::sort(randomCpy.begin(), randomCpy.end());
        auto end = clock.now();

        randomTime += std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    }

    // 2. Sorted Time
    std::chrono::milliseconds sortedTime(0);
    for (auto i = HOW_MANY_TIMES; i > 0; --i)
    {
        std::vector<int> sortedCpy(sorted.begin(), sorted.end());

        auto start = clock.now();
        std::sort(sortedCpy.begin(), sortedCpy.end());
        auto end = clock.now();

        sortedTime += std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    }

    // 3. Reversed Time
    std::chrono::milliseconds reversedTime(0);
    for (auto i = HOW_MANY_TIMES; i > 0; --i)
    {
        std::vector<int> reversedCpy(reversed.begin(), reversed.end());

        auto start = clock.now();
        std::sort(reversedCpy.begin(), reversedCpy.end());
        auto end = clock.now();

        reversedTime += std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    }

    // 4. Organ Pipe Time
    std::chrono::milliseconds organPipeTime(0);
    for (auto i = HOW_MANY_TIMES; i > 0; --i)
    {
        std::vector<int> organPipeCpy(organPipe.begin(), organPipe.end());

        auto start = clock.now();
        std::sort(organPipeCpy.begin(), organPipeCpy.end());
        auto end = clock.now();

        organPipeTime += std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    }

    // 5. Rotated Time
    std::chrono::milliseconds rotatedTime(0);
    for (auto i = HOW_MANY_TIMES; i > 0; --i)
    {
        std::vector<int> rotatedCpy(rotated.begin(), rotated.end());

        auto start = clock.now();
        std::sort(rotatedCpy.begin(), rotatedCpy.end());
        auto end = clock.now();

        rotatedTime += std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    }

    // Print stats
    std::cout << " --- std::vector Performance ---" << std::endl;
    std::cout << "Random Time     :" << randomTime.count() << " ms" << std::endl;
    std::cout << "Sorted Time     :" << sortedTime.count() << " ms" << std::endl;
    std::cout << "Reversed Time   :" << reversedTime.count() << " ms" << std::endl;
    std::cout << "Organ Pipe Time :" << organPipeTime.count() << " ms" << std::endl;
    std::cout << "Rotated Time    :" << rotatedTime.count() << " ms" << std::endl;
    std::cout << std::endl;
}
