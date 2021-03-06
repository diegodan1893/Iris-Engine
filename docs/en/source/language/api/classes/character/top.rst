The Character class
===================

In visual novels, text may consist of **narration**, which does not have a speaker,
and **dialogue**, which is labeled with the name of the character that is saying it.

In Iris Engine, dialogue is written using Character objects.
Once defined, these objects can be used in the same way as
:doc:`the say function<../../globals/say>`. See :ref:`using-characters-for-dialogue`
for a quick explanation on how to use them.


Properties
^^^^^^^^^^

.. toctree::
    :hidden:

    name

.. table::
    :widths: 1 1 1 100

    +----------+-------------------+------------------------+----------------------------------------+
    | Type     | Name              | Default value          | Description                            |
    +==========+===================+========================+========================================+
    | *string* | :doc:`name<name>` | Defined in constructor | Gets or sets the name of the character |
    +----------+-------------------+------------------------+----------------------------------------+


Member functions
^^^^^^^^^^^^^^^^

.. toctree::
    :hidden:

    constructor
    call

.. table::
    :widths: 1 100

    +-----------------------------------+-----------------------+
    | Method                            | Description           |
    +===================================+=======================+
    | :doc:`(constructor)<constructor>` | Create a character    |
    +-----------------------------------+-----------------------+
    | :doc:`__call metamethod<call>`    | Display dialogue text |
    +-----------------------------------+-----------------------+