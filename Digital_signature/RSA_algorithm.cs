using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Numerics;

namespace Digital_signature
{
    public static class RSA_algorithm
    {
        public static BigInteger EncryptData(BigInteger Data, Int64 differentPartOfKey, Int64 samePartOfKey)
        {
            return BigInteger.ModPow(Data, differentPartOfKey, samePartOfKey);
        }
    }
}
