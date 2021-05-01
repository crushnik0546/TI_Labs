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
        public static UInt64 EncryptData(UInt64 Data, Int64 publicKeyFirst, Int64 publicKeySecond)
        {
            UInt64 result = (UInt64)BigInteger.ModPow(Data, publicKeyFirst, publicKeySecond);
            return result;
        }

        public static UInt64 DecryptData(UInt64 Data, Int64 secretKeyFirst, Int64 secretKeySecond)
        {
            UInt64 result = (UInt64)BigInteger.ModPow(Data, secretKeyFirst, secretKeySecond);
            return result;
        }

    }
}
