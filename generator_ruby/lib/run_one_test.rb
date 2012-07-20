require "./generator_add.rb"
require "./generator_subtract.rb"
require "./generator_multiply.rb"
require "./generator_fract.rb"
require "./generator_floor_fp.rb"
require "./generator_divide.rb"

puts "=== Start ==="
gen = GeneratorDivide.new({"test_file_name" => "8_8/divide.test", "saturated" => false  , "type" => "8_8", "title" => "8_8 divide"});
gen.make_tests()
puts "=== Finish ==="