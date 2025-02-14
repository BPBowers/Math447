# Math447
## Book Cipher Validity Signature Producer (Final Project)

* A C++ program that applies several tests 
against a book ciphertext to mathematically calculate their “randomness,” with the primary purpose to determine the validity of the Beale Ciphers.

* The user can input examples of real and 
fake ciphertexts, and then compare the “signatures” each test provides against the signatures produced by the three Beale 
ciphertexts. 

* The algorithms include:
    1. The Komlmogorov-Smirnov test
    2. Chi-square test
    3. Serial Correlation test
    4. Mod Reduction Test
    5. Average Difference Test
    6. Run Up Test
    7. Run Down Test
    8. Last Digit Frequency Test
    9. All Digit Frequency Test
    10. Basic Stats Provider (Mean, Median, Number of Characters ect.)
    * The majority of the algorithms were found in the Art of 
Computer Programming Volume 2 by Donald Knuth.
* Also included under /CTGen is a small program that encrypting a message to produce a book ciphertext by randomly selecting the locations of letters in the provided key document, and removing the potential for that key location to be used again.
     

## Also Included
- Homework 4: Chapter 3 Computer Problems 1.1, 1.2, 2.2, 4 and 8
- Homework 6: Chapter 3 Computer Problems 6, 7, 12, and 13
- Homework 8: Miller Robin Primality test on 4 provided canidates
    1. 7849320745092875923486518746897436504752587

    2. 22439979015817429464453212582447889544084770603331770046950768541515493

    3. 67896375048456578490852086705286724507634897563894658714169752875923486518746897436504752807

    4. 7083387173976100946763005874138341859212076191416918191389884735307723848374461229436834907695854745003486953411841280531221745747218536839402506751247715594253113
- Homework 9: P-1 and Pollard Rho tests