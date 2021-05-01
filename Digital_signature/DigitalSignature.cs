using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Numerics;

namespace Digital_signature
{
    class DigitalSignature
    {
        private string data;
        private BigInteger digSign;

        // can be public or secret key
        private RSA_keys.Key key;

        public DigitalSignature(string textData, RSA_keys.Key rsaKey)
        {
            data = textData;
            key = new RSA_keys.Key();
            key = rsaKey;
            GenerateDigitalSignature();
        }

        public DigitalSignature(string textData, RSA_keys.Key rsaKey, BigInteger hashCode)
        {
            data = textData;
            key = new RSA_keys.Key();
            key = rsaKey;
            BigInteger dataHashCode = CalculateHash();
            digSign = RSA_algorithm.EncryptData(hashCode, key.differentPart, key.samePart);
            CheckDigitalSignature(dataHashCode);
        }

        public string GetData
        {
            get
            {
                return data;
            }
        }

        public BigInteger GetDigitalSignature
        {
            get
            {
                return digSign;
            }
        }

        private void GenerateDigitalSignature()
        {
            BigInteger hashCode = CalculateHash();
            Console.WriteLine($"Исходный хэш-код: {hashCode}");
            digSign = RSA_algorithm.EncryptData(hashCode, key.differentPart, key.samePart);
        }

        private BigInteger CalculateHash()
        {
            BigInteger prevH = 100;
            BigInteger currH = 0;
            byte[] byteData = Encoding.ASCII.GetBytes(data);
            for (Int64 i = 0; i < (Int64)data.Length; i++)
            {
                currH = BigInteger.Pow((prevH + byteData[i]), 2) % key.samePart;
                prevH = currH;
            }

            return currH;
        }

        private void CheckDigitalSignature(BigInteger recievedDataHachCode)
        {
            if (BigInteger.Compare(recievedDataHachCode, digSign) != 0)
            {
                Console.WriteLine($"Цифровые подписи не совпадают! ({recievedDataHachCode} != {digSign})");
            }
            else
            {
                Console.WriteLine($"Цифровые подписи совпадают ({recievedDataHachCode} == {digSign})");
            }
        }

    }
}
