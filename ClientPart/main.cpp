#include "mainwindow.h"
#include <QApplication>

//unsigned long long totalMem = 0;

//void* operator new(size_t size)
//{
//   totalMem += size;
//   qDebug() << totalMem;
//   void* p = malloc(size);
//   return p;
//}

//void operator delete(void* p, size_t size)
//{
//   totalMem -= size;
//   qDebug() <<"delete: "<< totalMem;
//   free(p);
//}

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
