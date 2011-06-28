#!/usr/bin/env ruby

good_items = [  "x: 1",
       "xx: 2",
       "_boo: 3",
       "_x1: 10",
       "xx : 2",
       "_boo  : 3",
       "x:4",
       "a: 139839",
       "a: -199999999999999999999999999999999999209420903902",
       "a: +13939",
       "a: 1.",
       "a: .1",
       "a: 0.1",
       "a: 10.2",
       "a: +10.34",
       "a: -9834.3",
       "a: 1e10",
       "a: 1E10",
       "a: +1E10",
       "a: +1E+10",
       "a: +1E-10",
       "a: -1E10",
       "a: -1E+10",
       "a: -1E-10" ,
       "a: 10.3e10",
       "a: 10.3e10",
       "a: +10.3e10",
       "a: +10.3e+10",
       "a: +10.3e-10",
       "a: -10.3E10",
       "a: -10.3E+10",
       "a: -10.3E-10" ,
       "a: infinity",
       "a: +infinity",
       "a: -infinity",
       "a: true",
       "a: false",
       'a: "true"',
       'a: "false"',
       "a: (1.0, -3.6)",
       "a: (1, -3.6)",
       "a: (1.0, -3)",
       "a: this_is_a_string",
       "a: 'this is a string'",
       'a: "this is a string"',
       "a: \"this\nhas\tstuff ok\"",
       'a: "this\nis\tverbatim\\ "'
       ]

bad_items =  [ 'a: 0.abc',
             'a: 0.abc:7' ]

#
# Need to figure out how to send single-quoted things to the parser.
#


def parse_item(text)
  txt = %x{echo \'#{text}\' | ./parser}
  rc = $?.exitstatus
  [rc, txt]
end

puts "Testing GOOD items"
good_items.each do |item|
  rc, txt = parse_item(item)
  if rc == 0
    print "."
  else
    puts "\nFAILURE for: #{item}"
    puts "\n"
    puts txt
  end
end

puts "testing BAD items"
bad_items.each do |item|
  rc, txt = parse_item(item)
  if rc != 0
    print "."
  else
    puts "\nFAILURE to reject: #{item}"
    puts "\n"
    puts txt
  end
end

