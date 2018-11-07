The Interpolator enum
=====================

An enumeration of interpolation functions used to control the acceleration of some
effects.


Values
------

+------------------------+--------------------+
| Value                  | Description        |
+========================+====================+
| Interpolator.linear    | Constant speed     |
+------------------------+--------------------+
| Interpolator.easeIn    | Slow start         |
+------------------------+--------------------+
| Interpolator.easeOut   | Slow end           |
+------------------------+--------------------+
| Interpolator.easeInOut | Slow start and end |
+------------------------+--------------------+


Remarks
-------

The following video shows the differences between these interpolation functions:

.. raw:: html

	<video width="560" height=315 controls loop style="margin-bottom:24px">
		<source src="../../../_static/interpolators.mp4" type="video/mp4">
	</video>