#ifndef MULTIVECTOR_H
#define MULTIVECTOR_H

#include <QVector>
#include <QMap>
#include <QString>
#include <initializer_list>

template <class T, int N>
class MultiVector
{
public:
	MultiVector(std::initializer_list<QString> types)
	{
		qDebug() << "Tamanho: " << types.size();
		map = new QMap<QString,QVector<T>*>();
		std::initializer_list<QString>::iterator it;
		for(it = types.begin(); it != types.end(); it++)
			map->insert(*it,new QVector<T>(N));
	}	

	QVector<T>* operator[](QString key)
	{
		return map->take(key);
	}

	QVector<T>* key(QString key)
	{
		return map->take(key);
	}


private:
	QMap<QString,QVector<T>*> *map;
	
};

#endif // MULTIVECTOR_H
