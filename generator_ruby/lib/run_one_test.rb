require "./generator_sqrt.rb"
require "./generator_subtract.rb"
require "./generator_multiply.rb"
require "./generator_fract.rb"
require "./generator_floor_fp.rb"
require "./generator_divide.rb"
require "./generator_sqrt.rb"

puts "=== Start ==="
gen = GeneratorLog.new({"test_file_name" => "8_8/sqrt.test", "saturated" => false  , "type" => "8_8", "title" => "8_8 sqrt"});
gen.make_tests()
puts "=== Finish ==="