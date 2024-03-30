# pet-TOPSIS-model :cat2: :dog2: :rabbit2: :mouse2: :lizard:
A TOPSIS model for calculating whether multiple households are suitable for keeping different pets. Whether these family are suitable for keeping pets is calculated as a number for 0 to 1.

## Sample input:

<img width="968" alt="Screenshot 2024-03-29 at 11 52 46 PM" src="https://github.com/HuaEdward/pet-TOPSIS-model/assets/102205131/09d546f6-c84b-4357-ae10-e74093fe6804">

Input to the code as: the specie of the pet (`Cat`, `Dog`, `Rabbit`, `Hamster`, `Lizard`)number of rows of the table + each number in the table (from column to row)

`Cat 6 1 7 4 7 3 7 78 2 0 1 10 3 7 10 27 1 1 8 7 5 5 4 62 4 0 9 20 3 18 5 32 2 1 10 100 4 22 18 45 0 0 4 50 8 15 9 38 3`

## After forwardization:

<img width="964" alt="Screenshot 2024-03-29 at 11 59 06 PM" src="https://github.com/HuaEdward/pet-TOPSIS-model/assets/102205131/458ee554-b1c5-4608-a1fd-a72e1f064532">

`1 7 4 7 3 7 0.536585 1 0 1 10 3 7 10 0.962963 1 1 8 7 5 5 4 0.926829 0.333333 0 9 20 3 18 5 1 1 1 10 100 4 22 18 1 1 0 4 50 8 15 9 1 0.666667`

## Sample output:

<img width="405" alt="Screenshot 2024-03-30 at 12 03 25 AM" src="https://github.com/HuaEdward/pet-TOPSIS-model/assets/102205131/90ba79f8-fe74-4ab8-86ce-11a73bddea22">

`0.63818 0.0880036 0.642584 0.305568 0.879334 0.26832`
