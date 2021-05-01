using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Digital_signature
{
    class RSA_keys
    {
        public struct PublicKey
        {
            public Int64 e;
            public Int64 n;
        }

        public struct SecretKey
        {
            public Int64 d;
            public Int64 n;
        }
        private readonly Int64[] fermaNumbers = { 17, 257, 65537 };
        private PublicKey pKey;
        private SecretKey sKey;
        Random rand;

        public RSA_keys()
        {
            rand = new Random();
            pKey = new PublicKey();
            sKey = new SecretKey();
            GenerateKeys();
        }

        public PublicKey GetPublicKey
        {
            get
            {
                return pKey;
            }
        }

        public SecretKey GetSecretKey
        { 
            get
            {
                return sKey;
            }
        }

        private void GenerateKeys()
        {
            Int64 p = FindSimpleNumber();
            Int64 q = FindSimpleNumber();
            Int64 n = p * q;
            Int64 eulerFunction = (p - 1) * (q - 1);
            Int64 e = fermaNumbers[rand.Next(0, 2)];

            pKey.e = e;
            pKey.n = n;

            sKey.d = GenerateSecretKey(e, eulerFunction);
            if (sKey.d < 0)
            {
                sKey.d = eulerFunction + sKey.d;
            }

            if (sKey.d == 0)
            {
                GenerateKeys();
            }
            else
            {
                sKey.n = n;
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
