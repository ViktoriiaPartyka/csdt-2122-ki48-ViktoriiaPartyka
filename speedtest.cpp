//test2, speedtest

#include "stdafx.h"
using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace TestMaxApp
{
    [TestClass]
    public ref class UnitTest1
    {
    private:
        TestContext^ testContextInstance;

    public:
        

        property Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ TestContext
        {
            Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ get()
            {
                return testContextInstance;
            }

            System::Void set(Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ value)
            {
                testContextInstance = value;
            }
        };

#pragma region Additional test attributes
        
#pragma endregion

        [TestMethod]
        void TestMethod1()
        {
            //
            // TODO: Add test logic here
            //
        };
    };
}