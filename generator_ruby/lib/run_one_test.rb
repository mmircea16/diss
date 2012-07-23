require "./generator_sqrt.rb"
require "./generator_subtract.rb"
require "./generator_multiply.rb"
require "./generator_fract.rb"
require "./generator_floor_fp.rb"
require "./generator_divide.rb"

puts "=== Start ==="
gen = GeneratorSqrt.new({"test_file_name" => "24_8/sqrt.test", "saturated" => false  , "type" => "24_8", "title" => "24_8 sqrt"});
gen.make_tests()
puts "=== Finish ==="