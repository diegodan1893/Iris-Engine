Character constructor
=====================

:Syntax: Character.new(*string* name)

Constructs a Character object with the specified name.


Parameters
^^^^^^^^^^

+----------+------+---------------------------------------------+
| Type     | Name | Description                                 |
+==========+======+=============================================+
| *string* | name | The name of the character used for dialogue |
+----------+------+---------------------------------------------+


Examples
^^^^^^^^

.. code-block:: lua

    -- Create Character objects for Haru and Sakura
    h = Character.new("Haru")
    s = Character.new("Sakura")

    -- Display dialogue using the variables we defined above
    h "Hi, my name is Haru."
    s "And I am Sakura."


See also
^^^^^^^^

* :doc:`name`
* :doc:`call`