using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Numerics;

namespace Digital_signature
{
    class Program
    {
        static void Main(string[] args)
        {
            RSA_keys keys = new RSA_keys();

            Console.Write("Исходный текст: ");
            string DataM = Console.ReadLine();

            DigitalSignature signatureM = new DigitalSignature(DataM, keys.GetSecretKey);
            BigInteger digSignM = signatureM.GetDigitalSignature;

            Console.WriteLine();
            Console.WriteLine($"Отправленные данные: {DataM}");
            Console.WriteLine($"Цифровая подпись: {digSignM}");
            Console.WriteLine();

            Console.WriteLine($"Полученные данные: {DataM}");
            DigitalSignature signatureRight = new DigitalSignature(DataM, keys.GetPublicKey, digSignM);

            StringBuilder badData = new StringBuilder(DataM);
            Random rand = new Random();
            badData[rand.Next(0, DataM.Length - 1)] = (char)rand.Next(65, 90);
            badData[rand.Next(0, DataM.Length - 1)] = (char)rand.Next(65, 90);

            Console.WriteLine();
            Console.WriteLine($"Полученные данные: {badData.ToString()}");
            DigitalSignature signatureBad = new DigitalSignature(badData.ToString(), keys.GetPublicKey, digSignM);

            Console.ReadLine();
        }
    }
}
