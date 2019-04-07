Rsa-crypt: main.cpp BigInteger.cpp Rsa.cpp RsaKey.h exceptions.h BigInteger.h Rsa.h
	c++ main.cpp BigInteger.cpp Rsa.cpp -o Rsa-crypt
	chmod +x ./Rsa-crypt
clean: Rsa-crypt
	rm ./Rsa-crypt
