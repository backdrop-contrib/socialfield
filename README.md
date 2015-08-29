Socialfield
============

The Social field module provides a single field that allows you to collect links
to multiple social networks like facebook, twitter, googleplus, linkedin, etc.

The links are presented as anchor tags with specific classes. These classes can
can be customized for each service. The classes can be used in conjunction with 
icon fonts (such as fontello or font awesome) to display the links as icons.

Links entered into social fields will be validated to assure they match the
service. Validation criteria can also be customized for each service.


Installation
------------

- Install this module using the official Backdrop CMS instructions at
  https://backdropcms.org/guide/modules

- Visit the configuration page under Administration > Configuration > Media >
  Socialfield (admin/config/category/foo) to configure available social
  services.

- Add social fields to any entity.


Sub-modules
-----------------

In addition to the core Social field module, you are able to enable the following sub-module:

* Font icons (font_icons): Loads fontello icons. You must download fontello library to sites/all/libraries/fontello folder. You can download fontello from http://fontello.com.


Permissions
-----------

The core Social field module defines permissions for viewing, creating, editing and deleting social services. All of these permissions can be found at admin/config/people/permissions.


License
-------

This project is GPL v2 software. See the LICENSE.txt file in this directory for
complete text.


Current Maintainers
-------------------

- Jen Lampton (https://github.com/jenlampton)
- Seeking additional comaintainers


Credits
-------

This module was originally written for Drupal by Mihai Husar
(https://www.drupal.org/u/mihai-husar) and was adapted for Backdrop CMS by Jen
Lampton (https://github.com/jenlampton)
