//
//  node.hpp
//  dataContainer
//
//  Created by Mingkai Chen on 2014-06-12.
//  Copyright © 2014-2016 Mingkai Chen. All rights reserved.
//

#pragma once
#ifndef __NODE__H
#define __NODE__H

// abstract class
template <class T>
class node
    {
    protected:
        T data;
        // shallow copy (change destructors if deep)
        virtual void dataInit(T data)
            {
            this->data = data;
            }
    public:
        virtual ~node() {}
        virtual void cascadeDelete ()   = 0;
        virtual node<T>* cascadeCopy () = 0;

        T getData () const
            {
            return data;
            }
    };

#endif /* __NODE__H */