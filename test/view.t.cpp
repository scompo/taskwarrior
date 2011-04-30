////////////////////////////////////////////////////////////////////////////////
// taskwarrior - a command line task list manager.
//
// Copyright 2006 - 2011, Paul Beckingham, Federico Hernandez.
// All rights reserved.
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software
// Foundation; either version 2 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License along with
// this program; if not, write to the
//
//     Free Software Foundation, Inc.,
//     51 Franklin Street, Fifth Floor,
//     Boston, MA
//     02110-1301
//     USA
//
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <Context.h>
#include <Column.h>
#include <Task.h>
#include <View.h>
#include <test.h>

Context context;

////////////////////////////////////////////////////////////////////////////////
int main (int argc, char** argv)
{
  UnitTest t (1);

  try
  {
    // Set up configuration.
    context.config.set ("fontunderline", true);
    context.config.set ("tag.indicator", "+");

    // Two sample tasks.
    Task t1 ("["
               "uuid:\"2a64f6e0-bf8e-430d-bf71-9ec3f0d9b661\" "
               "description:\"This is the description text\" "
               "project:\"Home\" "
               "priority:\"H\" "
               "tags:\"one,two\""
             "]");
    t1.id = 1;
    Task t2 ("["
               "uuid:\"f30cb9c3-3fc0-483f-bfb2-3bf134f00694\" "
               "description:\"This is the description text\" "
               "project:\"Garden Care\" "
               "depends:\"2a64f6e0-bf8e-430d-bf71-9ec3f0d9b661\""
             "]");
    t2.id = 11;

    std::vector <Task> data;
    data.push_back (t1);
    data.push_back (t2);

    // Sequence of tasks.
    std::vector <int> sequence;
    sequence.push_back (0);
    sequence.push_back (1);

    // Create colors.
    Color header_color (Color (Color::yellow, Color::nocolor, false, false, false));
    Color odd_color ("on gray1");
    Color even_color ("on gray0");

    // Create a view.
    View view;
    view.add (Column::factory ("id"));
    view.add (Column::factory ("uuid.short"));
    view.add (Column::factory ("project"));
    view.add (Column::factory ("priority.long"));
    view.add (Column::factory ("tags"));
    view.add (Column::factory ("tags.indicator"));
    view.add (Column::factory ("tags.count"));
    view.add (Column::factory ("description.truncated"));
    view.add (Column::factory ("depends"));
    view.width (100);
    view.leftMargin (4);
/*
    view.extraPadding (1);
*/
    view.extraPadding (0);
    view.intraPadding (1);
    view.colorHeader (header_color);
    view.colorOdd (odd_color);
    view.colorEven (even_color);
    view.intraColorOdd (odd_color);
    view.intraColorEven (even_color);
/*
    view.extraColorOdd (odd_color);
    view.extraColorEven (even_color);
*/

    // Render the view.
    std::cout << view.render (data, sequence);

    t.is (view.lines (), 3, "View::lines == 3");
  }

  catch (std::string& e)
  {
    t.fail ("Exception thrown.");
    t.diag (e);
  }

  return 0;
}

////////////////////////////////////////////////////////////////////////////////
