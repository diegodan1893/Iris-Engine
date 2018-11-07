The Transition enum
===================

An enumeration of transitions used to create *TransitionObjects*.


Values
------

+--------------------------+
| Value                    |
+==========================+
| Transition.none          |
+--------------------------+
| Transition.fade          |
+--------------------------+
| Transition.dissolve      |
+--------------------------+
| Transition.imageDissolve |
+--------------------------+


Remarks
-------

In Iris Engine, transitions are defined using Lua *tables*. For a *table* to correctly
define a transition, it must associate the ``type`` key to one of the values of the
Transition enum. In addition, each transition type may require additional keys to be
given a value. These keys are the *parameters* of the transition.

Here is a description of each transition type and its required parameters.


Transition.none
^^^^^^^^^^^^^^^

No transition, the change will be instant. It doesn't require additional parameters.

Example:

.. code-block:: lua

	{type=Transition.none}


Transition.fade
^^^^^^^^^^^^^^^

Used to make objects appear or disappear from the screen. The opacity of the object
will gradually change over time. Here are the required parameters:

+----------+-------+----------------------------------------------------------+
| Type     | Name  | Description                                              |
+==========+=======+==========================================================+
| *number* | time  | The duration in seconds of the transition                |
+----------+-------+----------------------------------------------------------+
| *bool*   | block | Whether this transition is a :term:`blocking transition` |
+----------+-------+----------------------------------------------------------+

Example:

.. code-block:: lua

	{type=Transition.fade, time=0.3, block=false}


Transition.dissolve
^^^^^^^^^^^^^^^^^^^

Used to smoothly transition from one image to another.

.. raw:: html

	<video width="560" height=315 controls loop style="margin-bottom:24px">
		<source src="../../../_static/scene_default.mp4" type="video/mp4">
	</video>

Here are the required parameters:

+----------+-------+----------------------------------------------------------+
| Type     | Name  | Description                                              |
+==========+=======+==========================================================+
| *number* | time  | The duration in seconds of the transition                |
+----------+-------+----------------------------------------------------------+
| *bool*   | block | Whether this transition is a :term:`blocking transition` |
+----------+-------+----------------------------------------------------------+

Example:

.. code-block:: lua

	{type=Transition.dissolve, time=0.5, block=false}


Transition.imageDissolve
^^^^^^^^^^^^^^^^^^^^^^^^

A dissolve transition controlled with a grayscale image, where black pixels in the
control image dissolve first and white pixels dissolve last. Here is a video showing
some examples. The control image used is shown in the top right corner.

.. raw:: html

	<video width="560" height=315 controls loop style="margin-bottom:24px">
		<source src="../../../_static/imageDissolve_examples.mp4" type="video/mp4">
	</video>

Here are the required parameters:

+----------+-------+--------------------------------------------------------------------------------------------+
| Type     | Name  | Description                                                                                |
+==========+=======+============================================================================================+
| *number* | time  | The duration in seconds of the transition                                                  |
+----------+-------+--------------------------------------------------------------------------------------------+
| *bool*   | block | Whether this transition is a :term:`blocking transition`                                   |
+----------+-------+--------------------------------------------------------------------------------------------+
| *string* | image | Path to the control image, relative to the *transitions* path specified in the config file |
+----------+-------+--------------------------------------------------------------------------------------------+

Example:

.. code-block:: lua

	{type=Transition.imageDissolve, time=1, image="wipe right.png", block=true}