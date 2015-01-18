# PHP Object Generator

PHP Object Generator, (POG) is an open source PHP code generator which automatically generates 
clean & tested Object Oriented code for your PHP4/PHP5 application. 

Over the years, it was realized that a large portion of a PHP programmer's time is wasted on 
repetitive coding of the Database Access Layer of an application simply because 
different applications require different objects. 

By generating PHP objects with integrated CRUD methods, POG gives you a head start in any project. 

The time you save can be spent on more interesting areas of your project.

## Install
* Extract repo content to a folder on your server
* Edit include/configuration.php
* Point your browser to /index.php


## Changes from POG

This version of POG was tailored for a specific web application, WINGS. Let's call it WPOG.

### Specific changes:
* List functions have been removed. In the future, another object should be created such as a Collection object that would have these List functions.
* First attribute is the Primary ID. This only works for combo PHP 5.1+, PDO and MySQL.

### Improvements for all:
Even with these changes, there are code improvements that will benefit to anyone wanting to implement POG in their environment.

Improved Javascript and made configuration more flexible:
* index.php
* index2.php
* include/configuration.php
* Changed any hardcoded URLs.
 
