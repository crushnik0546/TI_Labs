using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Digital_signature
{
    class RSA_keys
    {
        public struct Key
        {
            public Int64 differentPart;
            public Int64 samePart;
        }

        private readonly Int64[] fermaNumbers = { 17, 257, 65537 };
        private Key publicKey;
        private Key secretKey;
        Random rand;

        public RSA_keys()
        {
            rand = new Random();
            publicKey = new Key();
            secretKey = new Key();
            GenerateKeys();
        }

        public Key GetPublicKey
        {
            get
            {
                return publicKey;
            }
        }

        public Key GetSecretKey
        { 
            get
            {
                return secretKey;
            }
        }

        private void GenerateKeys()
        {
            Int64 p = FindSimpleNumber();
            Int64 q = FindSimpleNumber();
            Int64 n = p * q;
            Int64 eulerFunction = (p - 1) * (q - 1);
            Int64 e = fermaNumbers[rand.Next(0, 2)];

            publicKey.differentPart = e;
            publicKey.samePart = n;

            secretKey.differentPart = GenerateSecretKey(e, eulerFunction);
            if (secretKey.differentPart < 0)
            {
                secretKey.differentPart = eulerFunction + secretKey.differentPart;
            }

            if (secretKey.differentPart == 0)
            {
                GenerateKeys();
            }
            else
            {
                secretKey.samePart = n;
            }
        }

        private Int64 FindSimpleNumber()
        {
            Int64 number = 0;
            bool isSimple = false;

            while (!isSimple)
            {
                number = rand.Next(1000, 100000);
                isSimple = true;
                for (Int64 i = 2; i < Math.Sqrt(number); i++)
                {
                    if (number % i == 0)
                    {
                        isSimple = false;
                        break;
                    }
                }
            }
            return number;
        }

        private Int64 GenerateSecretKey(Int64 e, Int64 eulerFunction)
        {
            long x, y, d;
            EuclidEx(e, eulerFunction, out x, out y, out d);

            if (d == 1)
                return x;

            return 0;
        }

        private void EuclidEx(long a, long b, out long x, out long y, out long d)
        {
            long q, r, x1, x2, y1, y2;

            if (b == 0)
            {
                d = a;
                x = 1;
                y = 0;
                return;
            }

            x2 = 1;
            x1 = 0;
            y2 = 0;
            y1 = 1;

            while (b > 0)
            {
                q = a / b;
                r = a - q * b;
                x = x2 - q * x1;
                y = y2 - q * y1;
                a = b;
                b = r;
                x2 = x1;
                x1 = x;
                y2 = y1;
                y1 = y;
            }

            d = a;
            x = x2;
            y = y2;
        }
    }
}
