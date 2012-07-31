require "./generator_sqrt.rb"
require "./generator_subtract.rb"
require "./generator_multiply.rb"
require "./generator_fract.rb"
require "./generator_floor_fp.rb"
require "./generator_divide.rb"
require "./generator_log.rb"
require "./generator_exp.rb"

puts "=== Start ==="
gen = GeneratorDivide.new({"test_file_name" => "8_8/_divide.test", "saturated" => false  , "type" => "8_8", "title" => "8.8 divide"});
gen.make_tests()
puts "=== Finish ==="
