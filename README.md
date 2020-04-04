# OrderC

*OrderC* is a C module extension that order python list objects using functions written in C.

The aim of this module is show how to write an extension in C to extends the functionalities of Python. It is a silly example, but you will be able to see the best of both worlds.

Just enjoy.

## Instaling OrderC

      $ pip3 install git+https://github.com/rancavil/orderC.git

or 

     $ git clone https://github.com/rancavil/orderC.git
     $ cd orderC
     $ sudo python3 setup.py install

*Note:* You can use python 2 or 3.

## Example

*Note:* Currently we just implement the Bubble Sort and Selection Sort.

     $ python3
     Python 3.5.4 (default, Oct  9 2017, 12:07:29) 
     [GCC 6.4.1 20170727 (Red Hat 6.4.1-1)] on linux
     Type "help", "copyright", "credits" or "license" for more information.
     >>> import orderC
     >>> orderC.bubbleC([20,10,33,1,0,-1,2000,12,45,3])
     [-1, 0, 1, 3, 10, 12, 20, 33, 45, 2000]
     >>> 

## Methods

Currently, the module implements a bubble and selection sort.

     import orderC as ord
     resultbubble = ord.bubbleC([20,10,33,1,0,-1,2000,12,45,3])
     resultselection = ord.selectionC([20,10,33,1,0,-1,2000,12,45,3])




