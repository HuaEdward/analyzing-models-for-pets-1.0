# Model 1: Pet TOPSIS Model (PTM) (for :cat2: :dog2: :rabbit2: :mouse2: :lizard:)

* A TOPSIS (Technique for Order of Preference by Similarity to Ideal Solution) model for calculating whether multiple households are suitable for keeping different pets. Whether these family are suitable for keeping pets is calculated as a number for 0 to 1.

<img width="485" alt="Screenshot 2024-03-30 at 8 28 31 PM" src="https://github.com/HuaEdward/pet-TOPSIS-model-1.0/assets/102205131/dcc5f85e-999f-4616-9f0e-90cd7bc6a6b9">


## Sample input: 8 factors of certain amount of families to compare.

<img width="968" alt="Screenshot 2024-03-29 at 11 52 46 PM" src="https://github.com/HuaEdward/pet-TOPSIS-model/assets/102205131/09d546f6-c84b-4357-ae10-e74093fe6804">

* Input to the code as: the specie of the pet (`Cat`, `Dog`, `Rabbit`, `Hamster`, `Lizard`) + number of rows of the table + each number in the table (from column to row)

`Cat 6 1 7 4 7 3 7 78 2 0 1 10 3 7 10 27 1 1 8 7 5 5 4 62 4 0 9 20 3 18 5 32 2 1 10 100 4 22 18 45 0 0 4 50 8 15 9 38 3`

## After forwardization:

<img width="964" alt="Screenshot 2024-03-29 at 11 59 06 PM" src="https://github.com/HuaEdward/pet-TOPSIS-model/assets/102205131/458ee554-b1c5-4608-a1fd-a72e1f064532">

`1 7 4 7 3 7 0.536585 1 0 1 10 3 7 10 0.962963 1 1 8 7 5 5 4 0.926829 0.333333 0 9 20 3 18 5 1 1 1 10 100 4 22 18 1 1 0 4 50 8 15 9 1 0.666667`

## Sample output: A number from 0 to 1.

<img width="405" alt="Screenshot 2024-03-30 at 12 03 25 AM" src="https://github.com/HuaEdward/pet-TOPSIS-model/assets/102205131/90ba79f8-fe74-4ab8-86ce-11a73bddea22">

`0.63818 0.0880036 0.642584 0.305568 0.879334 0.26832`

* The larger the result value is, the more suitable the family is for this pet.


# Model 2: Multiple Pets TOPSIS Model (MPTM)

* The only difference is an extra factor => number of cats and dogs ​(if they have had cats or/and dogs)​.

## Sample input:

<img width="962" alt="Screenshot 2024-03-30 at 7 11 14 PM" src="https://github.com/HuaEdward/pet-TOPSIS-model-1.0/assets/102205131/2758e439-93a3-4c50-a134-48ebe1ab7545">

`Cat 6 1 7 4 7 3 7 78 2 0 0 1 10 3 7 10 27 1 1 1 8 7 5 5 4 62 4 0 0 9 20 3 18 5 32 2 2 1 10 100 4 22 18 45 0 3 0 4 50 8 15 9 38 3 2`

## Sample output:

<img width="330" alt="Screenshot 2024-03-30 at 8 13 42 PM" src="https://github.com/HuaEdward/pet-TOPSIS-model-1.0/assets/102205131/d544969e-ba42-4a79-9ce5-ea6ed8d8b157">

`0.662219 0.206854 0.667652 0.310214 0.720904 0.269207`

# Weights setting:

* The weights of the eight factors for different species are already calculated:

## PTM

`weightsC = {0.3453, 0.2018, 0.1249, 0.1144, 0.0679, 0.0679, 0.0389, 0.0389};
    weightsD = {0.2864, 0.1835, 0.1861, 0.1100, 0.0758, 0.0802, 0.0464, 0.0316};
    weightsH = {0.3395, 0.1432, 0.2034, 0.0830, 0.0552, 0.1107, 0.0382, 0.0267};
    weightsR = {0.3142, 0.2229, 0.1415, 0.0607, 0.1032, 0.0863, 0.0395, 0.0316};
    weightsL = {0.2542, 0.2955, 0.1453, 0.1162, 0.0791, 0.0570, 0.0313, 0.0214};`

Cat: <img width="346" alt="image" src="https://github.com/HuaEdward/pet-TOPSIS-model-1.0/assets/102205131/a16aeb7c-ede5-4600-87fe-2208fcbb8a6b">

Dog: <img width="354" alt="image" src="https://github.com/HuaEdward/pet-TOPSIS-model-1.0/assets/102205131/67f4e16b-99cc-4630-aab1-83eedf61949e">

Hamster: <img width="359" alt="image" src="https://github.com/HuaEdward/pet-TOPSIS-model-1.0/assets/102205131/7bdeeb0a-3212-436b-be0a-04d86f236df3">

Rabbit: <img width="378" alt="image" src="https://github.com/HuaEdward/pet-TOPSIS-model-1.0/assets/102205131/c85ebe2d-8b0f-4313-8a32-b4a728c4d5d9">

Lizard: <img width="369" alt="image" src="https://github.com/HuaEdward/pet-TOPSIS-model-1.0/assets/102205131/5f5bc84b-5966-4184-856c-645356edc192">

## MTP

`weightsC = {0.3044, 0.1806, 0.1084, 0.0941, 0.0564, 0.0564, 0.0332, 0.0332, 0.1333};
    weightsD = {0.2488, 0.1544, 0.1566, 0.0908, 0.0626, 0.0659, 0.0392, 0.0271, 0.1544};
    weightsH = {0.3107, 0.1337, 0.1825, 0.0713, 0.0492, 0.0930, 0.0339, 0.0239, 0.1019};
    weightsR = {0.2787, 0.2053, 0.1310, 0.0510, 0.0852, 0.0708, 0.0337, 0.0276, 0.1168};
    weightsL = {0.2367, 0.2778, 0.1397, 0.1087, 0.0777, 0.0501, 0.0280, 0.0194, 0.0618};`

Cat: <img width="611" alt="Screenshot 2024-03-30 at 7 57 51 PM" src="https://github.com/HuaEdward/pet-TOPSIS-model-1.0/assets/102205131/16b17a08-7a0f-441d-8f97-a6c84a8091b2">

Dog: <img width="464" alt="Screenshot 2024-03-30 at 7 58 31 PM" src="https://github.com/HuaEdward/pet-TOPSIS-model-1.0/assets/102205131/90aacae4-654a-4679-a965-f9a641118a6e">

Hamster: <img width="487" alt="Screenshot 2024-03-30 at 7 59 01 PM" src="https://github.com/HuaEdward/pet-TOPSIS-model-1.0/assets/102205131/7f03af81-bd50-4f1f-83b4-00b6948835dc">

Rabbit: <img width="439" alt="Screenshot 2024-03-30 at 7 59 22 PM" src="https://github.com/HuaEdward/pet-TOPSIS-model-1.0/assets/102205131/1c681d80-73a3-4418-b8e7-6af3b0d9fa6c">

Lizard: <img width="441" alt="Screenshot 2024-03-30 at 8 00 02 PM" src="https://github.com/HuaEdward/pet-TOPSIS-model-1.0/assets/102205131/61745691-a1a2-4bea-bd91-a8d00ed16ece">

