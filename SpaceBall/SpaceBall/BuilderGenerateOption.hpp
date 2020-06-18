#include "IOption.hpp"
#include "ArgumentOutOfRangeException.hpp"

enum BuilderGenerateOption
{
	notActivated,
	activated,
};

class BuilderGenerateOptions : public IOption
{
private:
	BuilderGenerateOption Option;

public:
	virtual void SetValue(int value)
	{
		Value = value;

		switch (value)
		{
		case 0:
			Option = notActivated;
			break;

		case 1:
			Option = activated;
			break;


		default:
			throw  new ArgumentOutOfRangeException("BuilderButtonSelectionOptions for value: " + std::to_string(value));
		}
	}

	BuilderGenerateOption Get() const
	{
		return Option;
	}

	void Reset()
	{
		SetValue(0);
	}
};