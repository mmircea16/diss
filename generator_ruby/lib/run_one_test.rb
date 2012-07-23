require "./generator_sqrt.rb"
require "./generator_subtract.rb"
require "./generator_multiply.rb"
require "./generator_fract.rb"
require "./generator_floor_fp.rb"
require "./generator_divide.rb"

puts "=== Start ==="
gen = GeneratorSqrt.new({"test_file_name" => "16_16/sqrt.test", "saturated" => false  , "type" => "16_16", "title" => "16_16 sqrt"});
gen.make_tests()
puts "=== Finish ==="