#ifndef _TREENODOAVL_
#define _TREENODOAVL_ 0

template <class T>
class treenodoAVL {

    private:
        T data;

    public:
        treenodoAVL* left = nullptr;
        treenodoAVL* right =  nullptr;
        treenodoAVL* father = nullptr;
        int diferencia;
        bool borrado;

        treenodoAVL(T pData) {
            data = pData;
            left = nullptr;
            right = nullptr;
            father = nullptr;
        }

        T getData() {
            return data;
        }

        void setData(T pValue) {
            this->data = pValue;
        }
};

#endif