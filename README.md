i wanted to know how Y-combinator works, so i wrote one with c++ metafunctions.  


## Y-combinator  
`Y-combinator` is a method of performing recursion without self-reference.  

## Z-combinator  
the standard definition however doesn't work for [applicative order](https://en.wikipedia.org/wiki/Evaluation_strategy#Applicative_order) languages.  so an alternative form needs to be used that is usually called a `Z-combinator`.  

## c++ meta-function
a meta-function is a type that contains a template alias.  this type can be then passed as a type parameter to templates like other meta-functions.  using meta-function is much more flexible and powerful that what can be achieved by using template template parameters.  

