require_relative '../../spec_helper'
require 'ostruct'

describe "OpenStruct#to_h" do
  before :each do
    @h = {name: "John Smith", age: 70, pension: 300}
    @os = OpenStruct.new(@h)
    @to_h = @os.to_h
  end

  it "returns a Hash with members as keys" do
    NATFIXME 'Implement OpenStruct#to_h', exception: SpecFailedException do
      @to_h.should == @h
    end
  end

  it "returns a Hash with keys as symbols" do
    os = OpenStruct.new("name" => "John Smith", "age" => 70)
    os.pension = 300
    NATFIXME 'Implement OpenStruct#to_h', exception: SpecFailedException do
      os.to_h.should == @h
    end
  end

  it "does not return the hash used as initializer" do
    @to_h.should_not equal(@h)
  end

  it "returns a Hash that is independent from the struct" do
    NATFIXME 'Implement OpenStruct getters', exception: NoMethodError, message: "undefined method `[]='" do
      @to_h[:age] = 71
      @os.age.should == 70
    end
  end

  context "with block" do
    it "converts [key, value] pairs returned by the block to a hash" do
      h = @os.to_h { |k, v| [k.to_s, v*2] }
      NATFIXME 'Implement OpenStruct#to_h', exception: SpecFailedException do
        h.should == { "name" => "John SmithJohn Smith", "age" => 140, "pension" => 600 }
      end
    end

    it "raises ArgumentError if block returns longer or shorter array" do
      NATFIXME 'Implement OpenStruct#to_h', exception: SpecFailedException do
        -> do
          @os.to_h { |k, v| [k.to_s, v*2, 1] }
        end.should raise_error(ArgumentError, /element has wrong array length/)

        -> do
          @os.to_h { |k, v| [k] }
        end.should raise_error(ArgumentError, /element has wrong array length/)
      end
    end

    it "raises TypeError if block returns something other than Array" do
      NATFIXME 'Implement OpenStruct#to_h', exception: SpecFailedException do
        -> do
          @os.to_h { |k, v| "not-array" }
        end.should raise_error(TypeError, /wrong element type String/)
      end
    end

    it "coerces returned pair to Array with #to_ary" do
      x = mock('x')
      x.stub!(:to_ary).and_return([:b, 'b'])

      NATFIXME 'Implement OpenStruct#to_h', exception: SpecFailedException do
        @os.to_h { |k| x }.should == { :b => 'b' }
      end
    end

    it "does not coerce returned pair to Array with #to_a" do
      x = mock('x')
      x.stub!(:to_a).and_return([:b, 'b'])

      NATFIXME 'Implement OpenStruct#to_h', exception: SpecFailedException do
        -> do
          @os.to_h { |k| x }
        end.should raise_error(TypeError, /wrong element type MockObject/)
      end
    end
  end
end
