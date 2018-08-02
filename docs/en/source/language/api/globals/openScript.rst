The openScript function
=======================

:Syntax: openScript(*string* file)
:Returns: This function does not return

This function will open and run the specified script. This script may be in source
form or precompiled.

The openScript function is similar to a goto statement in that the execution will
never return to the point where it was called from. This means that if there is any
code below a call to this function, it will **never** get executed.

.. note::

	All visible objects in the scene except for the background will be hidden.
	This might change in a future release.

.. warning::

	The path to the script may not contain any non-ASCII characters.
	This is not the case for images or sounds and will be fixed in a future
	release.


Parameters
^^^^^^^^^^

+----------+------+----------------------------------------------+
| Type     | Name | Description                                  |
+==========+======+==============================================+
| *string* | file | Path to the script; see remarks_ for details |
+----------+------+----------------------------------------------+


Remarks
^^^^^^^

The path of the *file* parameter must be relative to the *scripts* path
specified in the :doc:`config<../../../config>` file.


Examples
^^^^^^^^

.. code-block:: lua

    -- Open the script "chapter01.lua"
    openScript("chapter01.lua")

    -- This code will never be executed
    say "The player will not read this."