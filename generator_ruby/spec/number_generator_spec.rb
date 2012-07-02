require "../lib/number_generator.rb"
require "rspec"

describe NumberGenerator do
  
  before :all do
    @gen = NumberGenerator.new
  end
  
  it "should return string version for 8.8 numbers" do
    n = @gen.generate_fixed_point(8,8)
    /[01]{8}\.[01]{8}/.match(n).to_s.should eq(n)
  end
  
  it "should return string version for 16.16 numbers" do
      n = @gen.generate_fixed_point(16,16)
      /[01]{16}\.[01]{16}/.match(n).to_s.should eq(n)
    end
  
end