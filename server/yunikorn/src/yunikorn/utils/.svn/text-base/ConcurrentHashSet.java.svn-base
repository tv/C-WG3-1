package yunikorn.utils;
/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author testi
 */

import java.util.*;
public class ConcurrentHashSet<T> implements Set<T> {

    HashSet<T> decoratedSet;

    public int size() {
        return decoratedSet.size();
    }

    public boolean isEmpty() {
        return decoratedSet.isEmpty();
    }

    public boolean contains(Object o) {
        return decoratedSet.contains(o);
    }

    public Object[] toArray() {
        return decoratedSet.toArray();
    }

    public <T> T[] toArray(T[] a) {
        return decoratedSet.toArray(a);
    }

    public boolean containsAll(Collection<?> c) {
        return decoratedSet.containsAll(c);
    }
/* Above here are the stupid delegations which would produce no code, if we did subclassing instead */
    
    
    public boolean retainAll(Collection<?> c) {
        goStandaloneDecorators();
        return decoratedSet.retainAll(c);
    }

    
    
    
    public void clear() {
        goStandaloneDecorators();
        decoratedSet.clear();
    }
    
    HashSet<IteratorDecorator> runningIterators;
    //boolean iterating;
    public ConcurrentHashSet(int initialCapacity) {
        decoratedSet = new HashSet<T>(initialCapacity);
        runningIterators = new HashSet<IteratorDecorator>();
        
    }

    public ConcurrentHashSet(int initialCapacity, float loadFactor) {
        decoratedSet = new HashSet<T>(initialCapacity, loadFactor);
        runningIterators = new HashSet<IteratorDecorator>();
    }
    public ConcurrentHashSet() {

        decoratedSet = new HashSet<T>();
        runningIterators = new HashSet<IteratorDecorator>();
    
    }

    @Override
    public boolean add(T e) {
        goStandaloneDecorators();
        return decoratedSet.add(e);
    }

    @Override
    public boolean remove(Object o) {
        goStandaloneDecorators();
        return decoratedSet.remove(o);
    }

    @Override
    public boolean removeAll(Collection<?> c) {
        goStandaloneDecorators();
        return decoratedSet.removeAll(c);
    }

    @Override
    public boolean addAll(Collection<? extends T> c) {
        goStandaloneDecorators();
        return decoratedSet.addAll(c);
    }

    @Override
    public Iterator<T> iterator() {
        IteratorDecorator newIterator = new IteratorDecorator(decoratedSet.iterator());
        runningIterators.add(newIterator);
        return newIterator;
    }

   private void goStandaloneDecorators()
   {
   for (IteratorDecorator t : runningIterators)
   {
   t.goStandalone();
   }
   runningIterators.clear();
   }
    
    private class IteratorDecorator implements Iterator<T>
    {

    Iterator<T> decorate;
    T current;
    
        public IteratorDecorator(Iterator<T> decorate) {
            this.decorate = decorate;
            current = null;
            //index = 0;
        }

        public void remove() {
            
            decoratedSet.remove(current);
        }

        public T next() {
            
                
        return current = decorate.next();
        }

        public boolean hasNext() {
            boolean hasNext = decorate.hasNext();
            if (!hasNext)
            {
            runningIterators.remove(this);
            }
            return hasNext;
        }
 
     public void goStandalone()
    {
    LinkedList<T> iteratorBack = new LinkedList<T>();
    
    while (decorate.hasNext())
    {
    iteratorBack.add(decorate.next());
    }
    decorate = iteratorBack.iterator();
    
    
    }
    }
    

   




    

}
