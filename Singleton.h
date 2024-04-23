template <typename T>
class Singleton
{
protected:
  Singleton(void) {}
  ~Singleton(void) {}
public:
  static T* get(void)
  {
    static T* _inst = nullptr;
    if (!_inst)
      _inst = new T();
    return _inst;
  }
};

String xorstr_(String nString)
{
    const int KEY = 23;
    int strLen = (nString.length());
    char* cString = (char*)(nString.c_str());

    for (int i = 0; i < strLen; i++)
    {
        *(cString + i) = (*(cString + i) ^ KEY);
    }
    return nString;
}
