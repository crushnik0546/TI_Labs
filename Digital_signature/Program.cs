using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Digital_signature
{
    class Program
    {
        static void Main(string[] args)
        {
            RSA_keys keys = new RSA_keys();
            Console.WriteLine($"Public keys: e = {keys.GetPublicKey.e}  n = {keys.GetPublicKey.n}");
            Console.WriteLine($"Public keys: d = {keys.GetSecretKey.d}  n = {keys.GetSecretKey.n}");

            UInt64 hash = UInt64.Parse(Console.ReadLine());

            UInt64 chipher = RSA_algorithm.EncryptData(hash, keys.GetPublicKey.e, keys.GetPublicKey.n);
            Console.WriteLine($"Chipher data: {chipher}");
            UInt64 decryption = RSA_algorithm.DecryptData(chipher, keys.GetSecretKey.d, keys.GetSecretKey.n);
            Console.WriteLine($"Decrypted data: {decryption}");

            Console.ReadLine();

        }
    }
}
