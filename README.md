# Vector

1. Vectoriaus klasėje realizuotos pagrindinės funkcijos:
  1) push_back - įdeda elementą į galą, jeigu reikia padidinina vectoriaus dydį
  2) pop_back - išima paskutinį elementą
  3) operator[] - pasiekia nurodytą elementą
  4) at - pasiekia nurodytą elementą
  5) resize - keičia vectoriaus dydį
  6) erase - pašalina nurodytą elementą
  7) insert - įdeda elementą į nurodytą vietą
  
  ![Vector](https://user-images.githubusercontent.com/92882227/169871292-4da6d7ef-0bad-44d0-b4c9-33c9b95db8ee.PNG)
  
Visos funkcijos: (constructor), (destructor), operator=, assign, at, operator[], front, back, data, begin, cbegin, end, cend, rbegin, crbegin, rend, crend, capacity, empty, size, max_size, reserve, shrink_to_fit, clear, insert, emplace, erase, push_back, emplace_back, pop_back, resize, swap.

2. Vectorių užpildymo int tipo elementais spartos analizė:

| Container |   1000    |   10000   |   100000  |  1000000  | 10000000  |
|-----------|-----------|-----------|-----------|-----------|-----------|
|std::vector| 0.0000522 | 0.0004082 | 0.0035055 | 0.038663  | 0.385943  |
|MyVector   | 0.0000338 | 0.000311  | 0.0021738 | 0.0281966 | 0.234248  |

3. V2.0 užduoties konteinerių atminties perskirstymai užpildant 100000000 elementų:

| Container | Perskirstimų skaičius |
|-----------|-----------------------|
|std::vector| 40                    |
|MyVector   | 24                    |

4. V2.0 užduoties konteinerių spartos analizė:

|std::vector |   1000    |   10000   |   100000  |  1000000  | 10000000  |
|------------|-----------|-----------|-----------|-----------|-----------|
|Nuskaitymas | 0.0031912 | 0.0341387 |  0.235972 |  2.27346  |  22.1323  |
|Rūšiavimas  | 0.0023583 | 0.0193498 |  0.131255 |  1.51034  |  16.8996  |
|Išvedimas   | 0.0027067 | 0.0129009 |  0.0722602|  0.687996 |  6.91142  |

|MyVector   |   1000    |   10000   |   100000  |  1000000  | 10000000  |
|-----------|-----------|-----------|-----------|-----------|-----------|
|Nuskaitymas| 0.0032689 | 0.0257574 |  0.24814  |  2.42138  | 23.4903   |
|Rūšiavimas | 0.0044419 | 0.028236  | 0.308933  |  3.85529  | 28.6588   |
|Išvedimas  | 0.0017064 | 0.0091098 | 0.0793148 |  0.781831 | 7.92736   |
