#ifndef _QTPROMISE_QPROMISEHELPERS_H
#define _QTPROMISE_QPROMISEHELPERS_H

// QtPromise
#include "qpromise_p.h"

namespace QtPromise {

template <typename T>
typename QtPromisePrivate::PromiseDeduce<T>::Type qPromise(const T& value)
{
    using namespace QtPromisePrivate;
    using Promise = typename PromiseDeduce<T>::Type;
    return Promise([=](
        const QPromiseResolve<typename Promise::Type>& resolve,
        const QPromiseReject<typename Promise::Type>& reject) {
        PromiseFulfill<T>::call(value, resolve, reject);
    });
}

QPromise<void> qPromise()
{
    return QPromise<void>([](
        const QPromiseResolve<void>& resolve) {
        resolve();
    });
}

template <typename T>
QPromise<QVector<T> > qPromiseAll(const QVector<QPromise<T> >& promises)
{
    return QPromise<T>::all(promises);
}

QPromise<void> qPromiseAll(const QVector<QPromise<void> >& promises)
{
    return QPromise<void>::all(promises);
}

} // namespace QtPromise

#endif // _QTPROMISE_QPROMISEHELPERS_H
