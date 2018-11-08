Language reference
==================

Here you will learn how to write scripts for your games.

Iris Engine uses `Lua <https://www.lua.org/>`_ as its scripting language, so if
you are already familiar with it you can jump straight to the
:doc:`API Reference<api/top>`.

.. warning:: 
    Iris Engine expects all scripts to be saved in UTF-8. Not doing so will
    cause problems with non-ASCII characters.



Language basics
---------------

The script of an Iris Engine game is usually written in several *lua* files. These
files can be edited in any text editor, such as `Sublime Text`_,
`Visual Studio Code`_, or `Notepad++`_.

.. _Notepad++: https://notepad-plus-plus.org/
.. _Visual Studio Code: https://code.visualstudio.com/
.. _Sublime Text: https://www.sublimetext.com/

You can specify which script will be run first in the :doc:`config file<../config>`.

Comments
^^^^^^^^

Comments are parts of the script that are ignored by the game. They will help you
organize your scripts.

Comments start with a double hyphen (``--``) and run until the end of the line.
A comment can also span multiple lines if it starts with ``--[[`` and ends with
``]]``. Here is an example:

.. code-block:: lua

    -- This line is a comment and will be ignored by the game
    say "This part will be executed." -- This is a comment, too

    --[[
    This is a multiline comment.
    All of this text will be ignored by the game.
    ]]

However, a comment may not be part of a string:

.. code-block:: lua

    say "Hi. --This is not a comment and will be part of the narration."


Variables
^^^^^^^^^

Variables are a way of storing information for future use, and you will be using
them a lot. You don't have to worry about the details right now, as you will
quickly learn how to use them as you go.

Variables can be created by assigning any value to a name using the ``=`` operator:

.. code-block:: lua

    -- Create a variable called welcome that contains the text "Hi there!"
    welcome = "Hi there!"

    -- This will display the content of the variable as narration
    say (welcome)

All variables are global by default. That means you can use and modify the value of
the variable from any script in your game. You can limit the scope of a variable to
a single script or block by using the ``local`` keyword.

.. code-block:: lua

    -- This variable will only be known in the context it was defined
    local welcome = "Hi there!"

If a variable is declared as local, other scripts will behave as if it didn't
exist, so they will be able to define another variable with the same name
without modifying the original.

When a local and a global variable have the same name, the local one will take
precedence.



Dialogue and narration
----------------------

In visual novels, text may consist of **narration**, which does not have a
speaker, and **dialogue**, which is labeled with the name of the character that
is saying it.


The say function
^^^^^^^^^^^^^^^^

In Iris Engine, narration is written using the :doc:`say<api/globals/say>`
function. Here is an example of its usage:

.. code-block:: lua

    say "This is narration."
    say "You only need to write the 'say' keyword followed by the text in quotes."
    say "Easy, right?"

After each call to the say function, the game will display the text on the screen
and wait until the player clicks to dismiss it.

If your text contains quotation marks, you will need to precede them with a
backslash (``\``) to prevent them from closing the string:

.. code-block:: lua

    say "I saw a sign saying \"Mind the doors\"."

Alternatively, you can use single quotes to surround your text:

.. code-block:: lua

    say 'I saw a sign saying "Mind the doors"'


String concatenation
~~~~~~~~~~~~~~~~~~~~

Sometimes you will need to include the value of a variable in your narration. This
can be achieved with the ``..`` operator. Here is an example:

.. code-block:: lua

    -- Variable
    timesDefeated = 10

    -- Say with string concatenation
    say ("I was defeated " .. timesDefeated .. " times playing Rock–Paper–Scissors.")

This will be displayed as::

    I was defeated 10 times playing Rock-Paper-Scissors.

.. note::

    When calling the say function with anything that is not a literal string, such
    as a variable, a number, or the result of an operation like string
    concatenation, you will need to surround the argument in parentheses:

    .. code-block:: lua
    
        say (10)
        say ("There are " .. 10 .. " things.")
        welcome = "Hello!"
        say (welcome)


Line breaks and long text
~~~~~~~~~~~~~~~~~~~~~~~~~

You can enforce a line break by inserting ``\n`` in the middle of a string. For
example:

.. code-block:: lua

    say "This line contains\na line break."

This will be displayed as::

    This line contains
    a line break.

If the text to display is too long to fit in the :term:`text window`, the game will
split it automatically as if you had written it using multiple calls to the say function.


.. _using-characters-for-dialogue:

Defining characters
^^^^^^^^^^^^^^^^^^^

In order to write dialogue, that is, text that is labeled with the name of the character that is saying it, you will need to create a
:doc:`Character<api/classes/character/top>` object and store it in a variable. After
that, you will be able to use that variable the same way as `the say function`_.
Here is an example:

.. code-block:: lua

    -- Create Character objects for Haru and Sakura
    h = Character.new("Haru")
    s = Character.new("Sakura")

    -- Display dialogue using the variables we defined above
    h "Hi, my name is Haru."
    s "And I am Sakura."

The name of a character can be modified at any point by assigning a new value
to its ``name`` property:

.. code-block:: lua

    -- Characters
    h = Character.new("Haru")
    s = Character.new("???")

    -- Dialogue
    s "Good morning!"   --> The name will be displayed as "???"
    h "Hi. What's your name?"

    s.name = "Sakura"

    s ("My name is " .. s.name .. ". Nice to meet you.")



Choices, flags and control flow
-------------------------------

Functions
^^^^^^^^^

Before we can talk about choices, we must first introduce the concept of functions.

Functions are like little snippets of code that we save in a variable so that we
can execute them anytime we want. There are two equivalent ways to create
functions:

.. code-block:: lua

    -- We can create a function the same way we create variables
    sayHello = function()
        say "Hello!"
        say "I'm narrating from a function."
    end

    -- Or we can use this other syntax, which will produce the same result
    function anotherFunction()
        say "This is another function."
        say "It's called 'anotherFunction'."
    end

If you try to run this script, you will see it doesn't do anything. That is because
we created the functions but we never executed them. In order to execute a function
we need to **call** it using its name followed by ``()``. Here is an example where
we call two times one of the functions we just created:

.. code-block:: lua

    say "I am going to say hello."
    sayHello()
    say "You didn't hear me? No problem, I will repeat it."
    sayHello()

.. note:: 

    There is a lot more you can do with functions, this is only a short and
    simplified introduction to the concept so that we can explain the next topic.


Choices
^^^^^^^

Many visual novels ask the player to make choices that influence the outcome of
the story. In Iris Engine, this is done using
:doc:`Question<api/classes/question/top>` objects.

In order to present a choice to the player, you will need to create a Question
object and store it in a variable. Let's see an example:

.. code-block:: lua

    -- First, we define a function for each option
    function drink()
        say "I'm thirsty too. I should have a drink."
    end

    function iceCream()
        say "Ice cream is probably the best option."
    end

    -- Then we create a Question object by giving it a list of options and
    -- the corresponding functions to call when the player selects them
    q = Question.new({
        "Have a drink", drink,
        "Have an ice cream", iceCream
    })

    -- We can ask the player by calling q:ask()
    say "It's so hot here. What should I do?"
    q:ask()

.. note:: 

    The ``Question.new`` function takes a list of things as an argument. When
    this is the case, the parentheses are optional, so you can also write
    ``q = Question.new{ ... }``. This will save you some typing.

.. note::

    Note that when calling a function that works with an object, you will need to
    use the colon (``:``) operator instead of the dot (``.``) operator.

    That is why at the end we use ``q:ask()`` instead of ``q.ask()``.

You can also define the functions and create the Question object at the same time
like so:

.. code-block:: lua

    -- This time, we will define the functions while creating the question
    q = Question.new{
        "Have a drink", function()
            say "I'm thirsty too. I should have a drink."
        end,

        "Have an ice cream", function()
            say "Ice cream is probably the best option."
        end
    }

    -- Now we can ask the player to make the choice
    say "It's so hot here. What should I do?"
    q:ask()


Setting and checking flags
~~~~~~~~~~~~~~~~~~~~~~~~~~

Sometimes you will need to remember a choice the player has made so that it can
affect the story after a common section that will be the same regardless of what
was chosen. This is usually done using flags.

In Iris Engine, flags are just global variables_. For example, we can modify one
of the functions of the previous example so that it sets a flag:

.. code-block:: lua

    function iceCream()
        say "Ice cream is probably the best option."

        -- Here we set the flag to 'true'
        ateIceCream = true
    end

We can then check the ``ateIceCream`` flag using an **if** statement:

.. code-block:: lua

    if ateIceCream then
        -- This will be executed if ateIceCream was set to 'true'
        say "The ice cream I had yesterday was delicious."
    else
        -- This will be executed if ateIceCream was set to 'false'
        say "That ice cream looked delicious."
        say "I should go get one."
    end

.. note::

    If the value of a variable has not been set to anything, it will be evaluated
    as if it were set to ``false``.

Variables don't have to be either ``true`` or ``false``, they can store any kind
of data. For example, let's say your game includes a Rock–Paper–Scissors minigame
and you store the number of times the player was defeated in a variable called
``timesDefeated``. You can display a different dialogue depending on that number
with something like this:

.. code-block:: lua

    if timesDefeated == 0 then
        -- The player was defeated 0 times
        say "I'm the best Rock-Paper-Scissors player in the world."
    elseif timesDefeated < 3 then
        -- The player has been defeated 1 or 2 times
        say "I didn't win every match, but overall it wasn't that bad."
    else
        -- The player has been defeated 3 or more times
        say "Maybe I should quit this game."
    end


Questions without functions
~~~~~~~~~~~~~~~~~~~~~~~~~~~

It is also possible to create a Question object without using functions. In fact,
you can associate any kind of value to each option. After the call to the ``ask``
method, the ``answer`` property of your Question will contain the value associated
to the choice selected by the player. This can be useful in some cases. For
example, let's implement a coin flipping minigame:

.. code-block:: lua

    say "I have to choose heads or tails."

    -- We will associate a number to each option
    q = Question.new{
        "Heads", 0, -- A value of 0 will mean heads
        "Tails", 1  -- A value of 1 will mean tails
    }

    -- Ask the player to choose
    q:ask()

    -- Compare the answer with a randomly generated number between 0 and 1
    if q.answer == math.random(0, 1) then
        say "¡I won!"
    else
        say "¡No! ¡I lost!"
    end


Labels and the goto statement
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Labels allow you to assign a name to a specific point in a script. You can then use
the goto statement to transfer the execution of the script to that point.

.. code-block:: lua

    ::first::
        say "This will be executed first."

    ::second::
        say "And this will follow next."

    ::third::
        say "Now we will jump to the second label and create an infinite loop."
        goto second

Unlike with function calls, there is no way to return to where you've jumped from.

.. warning:: ..

    The goto statement has the following restrictions:
    
    * Goto statements can't be used to jump in or out of functions.
    * Goto statements can't jump after the declaration of a local variable.
      
    That means this will produce an error:

    .. code-block:: lua
    
        goto after -- Invalid jump
        local a = 0
        ::after::

    For more info, read `this article from the Lua wiki`_.
        
    .. _this article from the Lua wiki: http://lua-users.org/wiki/GotoStatement



API reference
-------------

Here you will find detailed information about all the functions and classes
available to you and how to use them.

.. toctree::
    :maxdepth: 2

    api/top